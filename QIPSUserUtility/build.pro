SUBDIRS               += utility.pro

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
deploy_app.commands       = make clean; rm -rf utility; make 
}

win32 {
run_app.commands       = Release/utility.exe

copy_app.commands      = copy /Y Release\utility.exe utility-dist\\

zip_app.commands       = zip -r utility-dist.zip utility-dist
}

unix:!macx {
run_app.commands       = killall utility; ./utility
}
