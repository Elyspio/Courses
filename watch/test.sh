#!/bin/bash
SESSION=$USER

tmux -2 new-session -d -s "$SESSION"

# Setup a window for tailing log files
tmux rename-window -t "$SESSION":0 'Logs'
tmux split-window -h
tmux next-layout

tmux select-pane -t 0
tmux send-keys 'nodemon  --ext c,h --watch ./src -x "clear && make test && ./dist/test/test.app"' C-m

tmux select-pane -t 1
# Set default window
tmux select-window -t "$SESSION":0

# Attach to session
tmux -2 attach-session -t "$SESSION"