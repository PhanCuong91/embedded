# barectf --metadata-dir=trace config.yaml
gcc -g -o example -I. example.c barectf.c barectf-platform-linux-fs.c
./example
babeltrace2 trace