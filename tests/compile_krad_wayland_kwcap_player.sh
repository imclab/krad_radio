gcc -g -Wall -I../tools/krad_wayland/ -I../tools/krad_wayland/ext/ -I../tools/krad_gui/ -I../tools/krad_system/ ../tools/krad_gui/krad_gui.c \
../tools/krad_wayland/krad_wayland.c ../tools/krad_wayland/kwcap-decode.c \
../tools/krad_system/krad_system.c krad_wayland_kwcap_player.c -o krad_wayland_kwcap_player \
 `pkg-config --libs --cflags gtk+-3.0 wayland-client` -lm
