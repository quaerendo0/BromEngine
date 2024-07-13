cd ./src
clang-format -i *.cpp *.h

Get-ChildItem -Path . -Directory -Recurse |
    foreach {
        cd $_.FullName
        &clang-format -i *.cpp *.h
    }