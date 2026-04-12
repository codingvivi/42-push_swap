root-dir := justfile_directory()

name := "push_swap"

tools-dir := root-dir / "tools"

build-dir := root-dir / "build"


bin-dir := build-dir / "bin"
bin-dir-src := bin-dir / "src"

bin-src := bin-dir-src / name

_default:
    @just -l

run *args:
    {{bin-src}} {{args}}
    
build *args:
    bear -- make {{args}}

brun bargs="" rargs="":
    just build {{bargs}}
    just run {{rargs}}

crun bargs="" rargs="":                                                                                     
      make clean
      just brun "{{bargs}}" "{{rargs}}"             

hrun bargs="" rargs="":
    make hclean
    just brun "{{bargs}}" "{{rargs}}"

visualize *args:
    make visualizer
    external/tools/push_swap_visualizer/build/bin/visualizer {{args}}

visualize-deps:
    sudo zypper install \
        cmake \
        gcc-c++ \
        clang \
        Mesa-libGL-devel \
        glu-devel \
        libX11-devel \
        libXrandr-devel \
        libudev-devel \
        freetype2-devel \
        sfml2-devel

test:
    make tester
    cd build/tester && bash push_swap_test_linux.sh

test-yfu:
    make tester-yfu
    cd build/tester-yfu/tester && bash basic_test.sh

test-yfu-loop size="100" count="10":
    make tester-yfu
    cd build/tester-yfu/tester && bash loop.sh {{size}} {{count}}
