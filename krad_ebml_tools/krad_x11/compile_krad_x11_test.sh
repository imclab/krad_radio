gcc -Wall krad_x11_test.c krad_x11.c -o krad_x11_test -std=c99 `pkg-config --libs --cflags xcb x11 gl xext xcb-atom cairo` -lX11-xcb -lrt -lxcb-image -lm
