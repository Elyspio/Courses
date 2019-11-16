#!/bin/bash
SESSION=$USER

tmux -2 new-session -d -s "$SESSION"

# Setup a window for tailing log files
tmux rename-window -t "$SESSION":0 'Logs'
tmux split-window -h
tmux split-window -h

tmux select-pane -t 2
tmux send-keys 'nodemon  --ext c,h --watch ./src -x "clear && make task"' C-m

tmux select-pane -t 1
tmux send-keys 'nodemon  --delay 1.5 --ext app --watch ./dist -x "clear && dist/server.app"' C-m

tmux select-pane -t 0
tmux send-keys 'nodemon  --delay 2.5 --ext app --watch ./dist -x "clear && dist/client.app"' C-m

# Set default window
tmux select-window -t "$SESSION":0

# Attach to session
tmux -2 attach-session -t "$SESSION"