# Contributing findings to this repository

Thank you for helping grow this **educational reverse-engineering** project.

We welcome **additional research, measurements, corrections, and documentation** from people who have studied the original binary, related hardware, or the rebuild packages.

> **Rules first:**  
> - Educational / defensive / documentation use only.  
> - **Do not** contribute guides aimed at illegal RF interference, attacking third-party networks, or bypassing law.  
> - See [DISCLAIMER.md](DISCLAIMER.md).

---

## How to contribute

### Option A — GitHub Pull Request (preferred)

1. Fork: https://github.com/ksanjeev284/esp32-combo-channel-select-re  
2. Create a branch: `findings/short-topic-name`  
3. Add your material under **`community/findings/YYYY-MM-DD_topic/`** (or improve `packages/`)  
4. Open a **Pull Request** with a clear title and short summary  
5. Maintainers will review for accuracy, safety, and fit  

**Firmware kits** live in numbered folders: [`packages/`](packages/) (`01-rebuild` … `06-lab-ultimate`).

### Option B — GitHub Issue (when you are not ready for a PR)

Open an issue with label-style title:

```text
[FINDING] short description
```

Include:

- What you found  
- How you found it (tool, address, measurement setup)  
- Evidence (hex dump snippet, Ghidra VA, photo, serial log, SHA256 of bin)  
- Suggested file path for the finding  

Issue templates are free-form; a PR with a filled template is still better when you have files.

---

## Where to put new material

| Kind of contribution | Put it here |
| --- | --- |
| **Community write-ups** (default) | [`community/findings/YYYY-MM-DD_short-title/`](community/findings/) |
| RE notes / corrections to analysis | `docs/` (or PR comment pointing to a community folder first) |
| New strings, dumps, Ghidra exports | `artifacts/` subfolder or `community/findings/.../evidence/` |
| Hardware measurements, pin variants | `community/findings/...` or Complete kit `…/hardware/` via PR |
| Firmware source improvements | `ESP32-ComboChannelSelect-Complete/<package>/src/` |
| IEEE / range / EDU research notes | matching package under `ESP32-ComboChannelSelect-Complete/` |
| Scripts (extractors, parsers) | `scripts/` |
| Ghidra helpers | `ghidra_scripts/` |

**Default for independent researchers:** use  
`community/findings/<date>_<slug>/`  
so your work is attributed and easy to review without rewriting the whole tree.

Copy the starter layout:

```text
community/findings/YYYY-MM-DD_short-title/
  README.md          ← required (use TEMPLATE)
  evidence/          ← optional dumps, logs, images
  notes.md           ← optional long form
```

Template: [`community/findings/TEMPLATE_FINDING.md`](community/findings/TEMPLATE_FINDING.md)

---

## What we especially want

- Corrections to VAs, pins, timings, or decompilation mistakes  
- Alternate board pinouts / schematics (with photos if possible)  
- Ghidra scripts, IDA/Ghidra databases **notes** (not huge binary DBs unless linked externally)  
- String xrefs, new function renames, call-graph insights  
- Lab measurements: range tables, SDR waterfalls, Vcc sag, hop_rate logs  
- Comparisons of original bin vs rebuild packages (SHA256, behavior)  
- IEEE / standards education notes that improve the NextLab docs  
- Translations of docs (keep legal disclaimer intact)  
- Safer UI-only (`REBUILD_SAFE`) improvements  

---

## What we will reject or ask to rewrite

- “How to jam public Wi‑Fi/BT in the wild” framing  
- Malware, exploits against third-party systems  
- Copyrighted full dumps of unrelated proprietary stacks without fair-use context  
- Unverifiable claims with no method or evidence  
- Secrets, credentials, personal data  
- Huge unrelated binaries (prefer links + hashes)  

---

## Finding quality bar

A useful contribution answers:

1. **Claim** — one clear sentence  
2. **Evidence** — address, screenshot, log, formula, or measurement  
3. **Method** — tool + steps so others can reproduce  
4. **Scope** — original bin only / rebuild / hardware variant  
5. **Limits** — what you did *not* verify  

---

## Attribution

In your `README.md` for the finding, include:

```markdown
## Author
- Name or handle:
- Contact (optional):
- Date:
- License for *your* text/data (e.g. CC-BY-4.0 or same as repo):
```

By submitting a PR, you agree your contribution may be redistributed under this repository’s [LICENSE](LICENSE), unless you clearly dual-license your materials in the finding folder.

---

## PR checklist

- [ ] Educational framing; no illegal-use instructions  
- [ ] Paths follow the table above  
- [ ] Finding `README.md` filled (if community finding)  
- [ ] Evidence or clear reproduction steps  
- [ ] No secrets / personal data  
- [ ] Linked from nowhere required — maintainers may index in `community/findings/README.md`  

---

## Questions

Open a GitHub **Discussion** or **Issue** titled `[QUESTION] …`.

Thank you for publishing research here so others can learn.
