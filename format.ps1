#clang-format -i *.cpp *.h

Get-ChildItem -Path ./src/ -Directory -Recurse |
    foreach {
        cd $_.FullName
        &clang-format -i *.cpp *.h
    }