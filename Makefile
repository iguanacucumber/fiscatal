all:
	meson compile -C build

deps:
	cd submodules/raylib/src && \
	make clean && \
	make PLATFORM=PLATFORM_DESKTOP RAYLIB_LIBTYPE=SHARED USE_WAYLAND_DISPLAY=TRUE USE_EXTERNAL_GLFW=TRUE -j8 && \
	sudo make install RAYLIB_LIBTYPE=SHARED && \
	sudo ln -sf /usr/local/lib/libraylib.so /usr/lib/libraylib.so && \
	cd ../../..

x11:
	cd submodules/raylib/src && \
	make clean && \
	make PLATFORM=PLATFORM_DESKTOP RAYLIB_LIBTYPE=SHARED USE_EXTERNAL_GLFW=TRUE -j8 && \
	sudo make install RAYLIB_LIBTYPE=SHARED && \
	sudo ln -sf /usr/local/lib/libraylib.so /usr/lib/libraylib.so && \
	cd ../../..

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
