root-dir := justfile_directory()

name := "push_swap"

tools-dir := root-dir / "tools"

build-dir := root-dir / "build"


bin-dir := build-dir / "bin"
bin-dir-src := bin-dir / "src"

bin-src := bin-dir-src / name

run *args:
    {{bin-src}} {{args}}
    
build *args:
    bear -- make {{args}}



