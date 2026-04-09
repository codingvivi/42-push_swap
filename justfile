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



visualizer *args:
    make visualizer
    external/tools/push_swap_visualizer/build/bin/visualizer {{args}}

visualizer-deps:
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
