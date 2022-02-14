#!/bin/bash
mkdir -p ~/.config/systemd/user/
cp ajSnapshotService.service effectsService.service gstreamerService.service jackServer.service ~/.config/systemd/user/
systemctl --user daemon-reload
systemctl --user enable effectsService
systemctl --user enable gstreamerService
systemctl --user enable ajSnapshotService