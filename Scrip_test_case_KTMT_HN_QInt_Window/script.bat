@echo off
setlocal enabledelayedexpansion
for /r %%i in (exe_sv\*) do (
    set filename=%%~ni
    echo !filename!
    rem running the binary file of student with format: 
    rem exe_sv\<MSSV>.exe data\input.txt output\<MSS>V_output.txt
    
    start /wait exe_sv\!filename!.exe data\input.txt output_sv\!filename!_output.txt
    rem compare file
    start bin\compare.exe output_sv\!filename!_output.txt data\output.txt grade_sv\!filename!_grade.txt
)
    