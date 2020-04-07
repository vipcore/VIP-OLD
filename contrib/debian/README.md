
Debian
====================
This directory contains files used to package vipd/vip-qt
for Debian-based Linux systems. If you compile vipd/vip-qt yourself, there are some useful files here.

## vip: URI support ##


vip-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install vip-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your vipqt binary to `/usr/bin`
and the `../../share/pixmaps/vip128.png` to `/usr/share/pixmaps`

vip-qt.protocol (KDE)

