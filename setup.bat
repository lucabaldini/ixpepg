@ECHO OFF
REM See this stackoverflow question
REM http://stackoverflow.com/questions/3827567/how-to-get-the-path-of-the-batch-script-in-windows
REM for the magic in this command
SET SETUP_DIR=%~dp0

SET IXPESWROOT=%SETUP_DIR%
SET IXPESWPYMODULES=%IXPESWROOT%ixpeswpy
SET PYTHONPATH=%PYTHONPATH%;%IXPESWROOT%

ECHO "IXPESWROOT set to " %IXPESWROOT%
