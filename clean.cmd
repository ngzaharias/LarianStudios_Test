@echo off
rd /s /q "%~dp0\Build\"
rd /s /q "%~dp0\Project\VisualStudio\.vs\"
rd /s /q "%~dp0\Project\VisualStudio\Intermediate\"
del /s /q "%~dp0\Project\VisualStudio\Breakout.VC.db"