#pragma once
/*
 * SoftAP web UI + optional captive portal + Web OTA (v0.4)
 * http://192.168.4.1/  ·  /ota  ·  /api/status
 */

#include <Arduino.h>
#include <WebServer.h>
#include <WiFi.h>
#include <Update.h>

#if ENABLE_CAPTIVE_PORTAL
#include <DNSServer.h>
#endif

struct LabWebHooks {
  const char* (*stateName)(int);
  int (*getState)();
  void (*setMode)(int);
  bool (*getArmed)();
  void (*arm)(bool on);
  void (*marker)();
  void (*pause)(bool on);
  bool (*getPause)();
  uint8_t (*chH)();
  uint8_t (*chV)();
  void (*setFixed)(int h, int v);
  float (*hopRate)();
  uint32_t (*hops)();
  uint16_t (*unique)();
  float (*vcc)();
  float (*busV)();
  float (*currA)();
  uint32_t (*markers)();
  uint32_t (*heap)();
  uint32_t (*trips)();  // current-limit trips
  const char* fwVersion;
  const char* hwName;
  const char* rateName;
};

class LabWeb {
 public:
  explicit LabWeb(LabWebHooks* h) : hooks_(h), server_(80), ok_(false) {}

  bool begin(const char* ssid, const char* pass, uint8_t channel) {
    WiFi.mode(WIFI_AP_STA);
    if (!WiFi.softAP(ssid, pass, channel)) {
      Serial.println(F("[WEB] softAP FAIL"));
      return false;
    }
    IPAddress ip = WiFi.softAPIP();
    Serial.printf("[WEB] SoftAP %s  http://%s/\n", ssid, ip.toString().c_str());

#if ENABLE_CAPTIVE_PORTAL
    dns_.start(53, "*", ip);
    Serial.println(F("[WEB] captive DNS * -> AP"));
#endif

    server_.on("/", HTTP_GET, [this]() { handleRoot(); });
    server_.on("/api/status", HTTP_GET, [this]() { handleApi(); });
    server_.on("/generate_204", HTTP_GET, [this]() {  // Android captive
      server_.sendHeader("Location", "http://192.168.4.1/");
      server_.send(302, "text/plain", "");
    });
    server_.on("/hotspot-detect.html", HTTP_GET, [this]() {  // Apple
      server_.sendHeader("Location", "http://192.168.4.1/");
      server_.send(302, "text/plain", "");
    });
    server_.on("/arm", HTTP_GET, [this]() {
      if (hooks_ && hooks_->arm) hooks_->arm(true);
      redirectHome();
    });
    server_.on("/disarm", HTTP_GET, [this]() {
      if (hooks_ && hooks_->arm) hooks_->arm(false);
      redirectHome();
    });
    server_.on("/marker", HTTP_GET, [this]() {
      if (hooks_ && hooks_->marker) hooks_->marker();
      redirectHome();
    });
    server_.on("/pause", HTTP_GET, [this]() {
      if (hooks_ && hooks_->pause) hooks_->pause(true);
      redirectHome();
    });
    server_.on("/resume", HTTP_GET, [this]() {
      if (hooks_ && hooks_->pause) hooks_->pause(false);
      redirectHome();
    });
    server_.on("/mode", HTTP_GET, [this]() {
      if (server_.hasArg("n") && hooks_ && hooks_->setMode)
        hooks_->setMode(server_.arg("n").toInt());
      redirectHome();
    });
    server_.on("/fixed", HTTP_GET, [this]() {
      int h = server_.hasArg("h") ? server_.arg("h").toInt() : 45;
      int v = server_.hasArg("v") ? server_.arg("v").toInt() : 55;
      if (hooks_ && hooks_->setFixed) hooks_->setFixed(h, v);
      if (hooks_ && hooks_->setMode) hooks_->setMode(7);
      redirectHome();
    });

#if ENABLE_WEB_OTA
    server_.on("/ota", HTTP_GET, [this]() { handleOtaForm(); });
    server_.on(
        "/update", HTTP_POST,
        [this]() {
          server_.sendHeader("Connection", "close");
          server_.send(200, "text/plain", Update.hasError() ? "OTA FAIL" : "OTA OK — rebooting");
          delay(500);
          ESP.restart();
        },
        [this]() { handleOtaUpload(); });
#endif

    server_.onNotFound([this]() {
      // Captive: bounce unknown paths to portal
      if (!server_.hostHeader().startsWith("192.168.4.")) {
        server_.sendHeader("Location", "http://192.168.4.1/");
        server_.send(302, "text/plain", "");
        return;
      }
      server_.send(404, "text/plain", "not found");
    });
    server_.begin();
    ok_ = true;
    return true;
  }

  void loop() {
#if ENABLE_CAPTIVE_PORTAL
    dns_.processNextRequest();
#endif
    if (ok_) server_.handleClient();
  }

  bool ok() const { return ok_; }

 private:
  LabWebHooks* hooks_;
  WebServer server_;
  bool ok_;
#if ENABLE_CAPTIVE_PORTAL
  DNSServer dns_;
#endif

  void redirectHome() {
    server_.sendHeader("Location", "/");
    server_.send(302, "text/plain", "ok");
  }

  void handleApi() {
    if (!hooks_) {
      server_.send(500, "application/json", "{}");
      return;
    }
    char buf[640];
    snprintf(buf, sizeof(buf),
             "{\"fw\":\"%s\",\"mode\":%d,\"name\":\"%s\",\"armed\":%s,\"pause\":%s,"
             "\"chH\":%u,\"chV\":%u,\"hop_rate\":%.1f,\"hops\":%lu,\"unique\":%u,"
             "\"vcc\":%.2f,\"busV\":%.2f,\"currA\":%.3f,\"markers\":%lu,\"heap\":%u,"
             "\"trips\":%lu,\"hw\":\"%s\",\"rate\":\"%s\"}",
             hooks_->fwVersion ? hooks_->fwVersion : "?",
             hooks_->getState ? hooks_->getState() : 0,
             hooks_->stateName && hooks_->getState ? hooks_->stateName(hooks_->getState()) : "?",
             hooks_->getArmed && hooks_->getArmed() ? "true" : "false",
             hooks_->getPause && hooks_->getPause() ? "true" : "false",
             hooks_->chH ? (unsigned)hooks_->chH() : 0,
             hooks_->chV ? (unsigned)hooks_->chV() : 0,
             hooks_->hopRate ? hooks_->hopRate() : 0.0f,
             hooks_->hops ? (unsigned long)hooks_->hops() : 0UL,
             hooks_->unique ? (unsigned)hooks_->unique() : 0,
             hooks_->vcc ? hooks_->vcc() : 0.0f,
             hooks_->busV ? hooks_->busV() : 0.0f,
             hooks_->currA ? hooks_->currA() : 0.0f,
             hooks_->markers ? (unsigned long)hooks_->markers() : 0UL,
             hooks_->heap ? (unsigned)hooks_->heap() : 0,
             hooks_->trips ? (unsigned long)hooks_->trips() : 0UL,
             hooks_->hwName ? hooks_->hwName : "?",
             hooks_->rateName ? hooks_->rateName : "?");
    server_.send(200, "application/json", buf);
  }

  void handleRoot() {
    String html;
    html.reserve(2800);
    html += F("<!DOCTYPE html><html><head><meta charset=utf-8>"
              "<meta name=viewport content=\"width=device-width,initial-scale=1\">"
              "<meta http-equiv=refresh content=5>"
              "<title>LabUltimate</title>"
              "<style>body{font-family:sans-serif;margin:12px;background:#0d1117;color:#e6edf3}"
              "a.btn{display:inline-block;margin:4px;padding:10px 12px;background:#238636;"
              "color:#fff;text-decoration:none;border-radius:6px;font-size:.9rem}"
              "a.danger{background:#da3633}a.warn{background:#9e6a03}a.sec{background:#1f6feb}"
              "pre{background:#161b22;padding:10px;border-radius:6px;overflow:auto}"
              "h1{font-size:1.25rem}</style></head><body>");
    html += F("<h1>Lab Ultimate TX</h1>");
    if (hooks_) {
      html += "<pre>";
      html += "fw: ";
      html += hooks_->fwVersion ? hooks_->fwVersion : "?";
      html += "\nmode: ";
      if (hooks_->getState && hooks_->stateName)
        html += hooks_->stateName(hooks_->getState());
      html += "\narmed: ";
      html += (hooks_->getArmed && hooks_->getArmed()) ? "YES" : "NO";
      html += "  pause: ";
      html += (hooks_->getPause && hooks_->getPause()) ? "YES" : "NO";
      html += "\nchH/V: ";
      html += String(hooks_->chH ? hooks_->chH() : 0);
      html += "/";
      html += String(hooks_->chV ? hooks_->chV() : 0);
      html += "\nhop/s: ";
      html += String(hooks_->hopRate ? hooks_->hopRate() : 0, 1);
      html += "\nI: ";
      html += String(hooks_->currA ? hooks_->currA() : 0, 3);
      html += " A  bus: ";
      html += String(hooks_->busV ? hooks_->busV() : 0, 2);
      html += " V\ntrips: ";
      html += String(hooks_->trips ? hooks_->trips() : 0);
      html += "  heap: ";
      html += String(hooks_->heap ? hooks_->heap() : 0);
      html += "</pre>";
    }
    html += F("<p>"
              "<a class='btn' href='/arm'>Arm</a>"
              "<a class='btn danger' href='/disarm'>Disarm</a>"
              "<a class='btn warn' href='/marker'>Marker</a>"
              "<a class='btn' href='/pause'>Pause</a>"
              "<a class='btn' href='/resume'>Resume</a>"
              "</p><p><b>Modes</b><br>");
    const char* labels[] = {"", "BT", "BLE", "WiFi", "RC", "154", "COEX",
                            "FIXED", "SLOW", "CSA1", "CSA2", "BLESCAN"};
    for (int i = 1; i <= 11; i++) {
      html += "<a class='btn sec' href='/mode?n=";
      html += String(i);
      html += "'>";
      html += labels[i];
      html += "</a>";
    }
    html += F("</p><p><b>Fixed</b><br>"
              "<a class='btn' href='/fixed?h=45&v=55'>45/55</a>"
              "<a class='btn' href='/fixed?h=2&v=26'>BLE 2/26</a>"
              "<a class='btn' href='/fixed?h=12&v=37'>WiFi 1/6</a>"
              "<a class='btn' href='/fixed?h=37&v=62'>WiFi 6/11</a>"
              "</p><p>"
              "<a href='/api/status'>JSON</a> · "
#if ENABLE_WEB_OTA
              "<a href='/ota'>OTA Update</a> · "
#endif
              "refresh 5s</p>"
              "<p style='opacity:.55;font-size:.8rem'>Authorized lab only</p></body></html>");
    server_.send(200, "text/html", html);
  }

#if ENABLE_WEB_OTA
  void handleOtaForm() {
    server_.send(200, "text/html",
                 F("<!DOCTYPE html><html><body style='font-family:sans-serif;background:#111;color:#eee;padding:16px'>"
                   "<h2>LabUltimate OTA</h2>"
                   "<p>Upload a <b>.bin</b> app image (not full 4MB merge unless you know offsets).</p>"
                   "<form method='POST' action='/update' enctype='multipart/form-data'>"
                   "<input type='file' name='update' accept='.bin'>"
                   "<button type='submit'>Flash & Reboot</button></form>"
                   "<p><a href='/'>Back</a></p></body></html>"));
  }

  void handleOtaUpload() {
    HTTPUpload& upload = server_.upload();
    if (upload.status == UPLOAD_FILE_START) {
      Serial.printf("[OTA] start %s\n", upload.filename.c_str());
      if (!Update.begin(UPDATE_SIZE_UNKNOWN)) {
        Update.printError(Serial);
      }
    } else if (upload.status == UPLOAD_FILE_WRITE) {
      if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
        Update.printError(Serial);
      }
    } else if (upload.status == UPLOAD_FILE_END) {
      if (Update.end(true)) {
        Serial.printf("[OTA] success %u bytes\n", upload.totalSize);
      } else {
        Update.printError(Serial);
      }
    }
  }
#endif
};
