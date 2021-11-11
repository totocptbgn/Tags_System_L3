.SILENT: clean build all

all:
	./install.sh

.PHONY: clean
clean:
	rm -rf build/ ~/.tag && \
	(for i in $(seq 1 5); do sed -i '$d' ../.bashrc; done;) && \
	echo "Please relaunch your terminal."

.PHONY: build
build:
	rm -rf build/
	./build.sh
