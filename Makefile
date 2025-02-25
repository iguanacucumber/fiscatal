all:
	meson compile -C build

setup:
	meson setup build --buildtype=release --reconfigure

pgo: # WIP
	meson setup build --buildtype=release -Db_pgo=generate --reconfigure
	meson compile -C build

	meson configure build -Db_pgo=use
	meson compile -C build

clean:
	rm -rf build .cache config.ini
	mkdir build
