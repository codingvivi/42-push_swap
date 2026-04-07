const BIN = "build/bin/src/push_swap"

def main [] {
    print "=== push_swap tester ==="

    # Error cases
    let results = [
        (test-case "no args" [] {exit_code: 1, stderr: "Error\n"})
        (test-case "non-numeric" ["a"] {exit_code: 1, stderr: "Error\n"})
        (test-case "mixed invalid" ["1" "b" "3"] {exit_code: 1, stderr: "Error\n"})
        (test-case "overflow" ["2147483648"] {exit_code: 1, stderr: "Error\n"})
        (test-case "underflow" ["-2147483649"] {exit_code: 1, stderr: "Error\n"})
        # Sorting cases
        (test-case "single element" ["42"] {exit_code: 0, stdout: ""})
        (test-case "already sorted 2" ["1" "2"] {exit_code: 0, stdout: ""})
        (test-case "already sorted 3" ["1" "2" "3"] {exit_code: 0, stdout: ""})
        (test-case "two elements" ["2" "1"] {exit_code: 0})
        (test-case "three elements" ["3" "2" "1"] {exit_code: 0})
        (test-case "six elements" ["9" "32" "93" "88" "21" "1"] {exit_code: 0})
        # Single string arg
        (test-case "single string" ["3 2 1"] {exit_code: 0})
    ]

    let tests = $results | length
    let passed = $results | where $t  

    

    for r in $results {
        if $r {
            $passed = $passed + 1
        } else {
            $failed = $failed + 1
        }
    }
    print $"\n($passed) passed, ($failed) failed"
    if $failed > 0 { exit 1 }
}

def test-case [name: string, args: list<string>, expected: record] {
    let actual = run-bin $args
    let exp = $expected | transpose key expected
    let act = $actual | transpose key actual
    let all = $exp | merge $act
    let failures = $all | where { |row|
        ($row | get -o expected) != null and $row.expected != $row.actual
    }
    if ($failures | is-empty) {
        print $"  ✓ ($name)"
    } else {
        print $"  ✗ ($name)"
        $failures | each { |row|
            print $"    ($row.key): expected=($row.expected) actual=($row.actual)"
        }
    }
    $failures | is-empty
}

def run-bin [args: list<string>] -> record {
    let result = if ($args | is-empty) {
        ^$BIN | complete
    } else {
        ^$BIN ...$args | complete
    }
    {
        exit_code: $result.exit_code
        stdout: $result.stdout
        stderr: $result.stderr
    }
}
