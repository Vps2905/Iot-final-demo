# Vijay P S — Embedded & IoT Projects

[Portfolio](https://vijaypsportfolio.vercel.app/) · [LinkedIn](https://www.linkedin.com/in/vijay-ps-362a66298/) · [Project index](https://github.com/Vps2905/warehouse-autonomous-robot/blob/main/docs/PROJECT_INDEX.md)

This repository retains the existing ESP32-S3 footfall firmware and Flask backend, and adds reviewable public references for the smart dustbin and solar-cleaning robot described on my LinkedIn profile.

## Public embedded examples

Start with [portfolio_projects/README.md](portfolio_projects/README.md): it includes ESP32 sketches, the C++ control logic shared by the sketches, desktop controller tests, sample JSON telemetry and a SQLite serial/file importer. These are new independent reconstructions, not recovered original prototype firmware. Board compilation and physical operation were not tested here.

## Existing footfall source

- `firmware/footfall_pilot_v3_arduino/`: original ESP32-S3 firmware and type definitions.
- `backend/app.py`: Flask ingestion, audience qualification, partner simulation and dashboard backend.
- `backend/static/`, `backend/templates/`: browser dashboard.
- `backend/requirements.txt`, root `requirements.txt`, `Dockerfile`, `Procfile`: existing deployment files.

Configure locally supplied `INGEST_API_KEY`, `ADMIN_API_KEY` and, when needed, `FSQ_API_KEY`. Credentials and a permitted test data source are required. The Foursquare code path needs an actual API key; LiveRamp, GroundTruth and DSP paths are simulations. They do not demonstrate real advertising delivery or approved identity matching. No company backend deployment, live partner call or physical ESP32 test was performed during the public-project restoration.

Keep runtime credentials outside Git. The new examples contain no Wi-Fi passwords, API tokens, customer data or original client source. Existing footfall firmware/backend code was preserved rather than rewritten as a new project.
