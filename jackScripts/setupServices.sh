#!/bin/bash
cp ../build/bin/effectsApp ./effectsApp
sudo mkdir -p /var/lib/jackAssets
sudo cp -a . /var/lib/jackAssets/
mkdir -p ~/.config/systemd/user/
cp ajSnapshotService.service effectsService.service gstreamerService.service jackServer.service ~/.config/systemd/user/
systemctl --user daemon-reload
systemctl --user enable effectsService
systemctl --user enable gstreamerService
systemctl --user enable ajSnapshotService
