SUBDIRS               += QIPS.pro

TEMPLATE               = subdirs

QMAKE_EXTRA_TARGETS   += run_app
run_app.target         = run
run_app.depends        = first

QMAKE_EXTRA_TARGETS   += zip_app
zip_app.target         = zip
zip_app.depends        = copy

QMAKE_EXTRA_TARGETS   += copy_app
copy_app.target        = copy
copy_app.depends       = first

QMAKE_EXTRA_TARGETS   += deploy_app
copy_app.target        = deploy
copy_app.depends       = first

macx  {
deploy_app.commands       = make clean; rm -rf QIPS; make 
}

win32 {
run_app.commands       = Release/QIPS.exe

copy_app.commands      = copy /Y Release\QIPS.exe qips-dist\\

zip_app.commands       = zip -r QIPS-dist.zip QIPS-dist
}

unix:!macx {
run_app.commands       = killall QIPS; ./QIPS
}
