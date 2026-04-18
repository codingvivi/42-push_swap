root-dir := justfile_directory()

name := "push_swap"


src-dir := root-dir / "src"
build-dir := root-dir / "build"
bin-dir := build-dir / "bin"
bin-src := bin-dir / "src" / "push_swap"

stage-dir := build-dir / "dist/push_swap_turnin_"


_default:
    @just -l


# =============================================================================
# build
# =============================================================================

# run the built binary with the given args
[group('build')]
run *args:
    {{bin-src}} {{args}}

# build via bear to refresh compile_commands.json
[group('build')]
build *args:
    bear -- make {{args}}

# build then run (bargs → build, rargs → run)
[group('build')]
brun bargs="" rargs="":
    just build {{bargs}}
    just run {{rargs}}

# clean, build, run
[group('build')]
crun bargs="" rargs="":
      make clean
      just brun "{{bargs}}" "{{rargs}}"

# full rebuild (make re) then run
[group('build')]
rerun *args:
    make re
    just run {{args}}


# =============================================================================
# dist
# =============================================================================

# full checks (norm + rebuild + tests) then package tarball
[group('dist')]
dist-safe *args:
    just checks-dist-full
    make dist {{args}}

# quick checks (norm + rebuild) then package tarball
[group('dist')]
dist *args:
    just checks-dist
    make dist {{args}}

# norm + rebuild + run the test suite
[group('dist')]
checks-dist-full:
    just checks-dist
    just test

# rebuild + norminette
[group('dist')]
checks-dist:
    make re
    just test-norm


# =============================================================================
# test
# =============================================================================

# run norminette across src/ (skipping header check)
[group('test')]
test-norm:
    cd {{src-dir}} && norminette -R CheckForbiddenSourceHeaders

# stage + run the default 42 tester
[group('test')]
test:
    make tester
    cd build/tester && bash push_swap_test_linux.sh

# stage + run yfu's tester (single pass)
[group('test')]
test-yfu:
    make tester-yfu
    cd build/tester-yfu/tester && bash basic_test.sh

# stage + run yfu's loop tester N times at given size
[group('test')]
test-yfu-loop size="100" count="10":
    make tester-yfu
    cd build/tester-yfu/tester && bash loop.sh {{size}} {{count}}


# =============================================================================
# tools
# =============================================================================

# launch the push_swap visualizer on the given input
[group('tools')]
visualize *args:
    make visualizer
    external/tools/push_swap_visualizer/build/bin/visualizer {{args}}

# install visualizer build deps (openSUSE Tumbleweed)
[group('tools')]
visualize-deps-tw:
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
