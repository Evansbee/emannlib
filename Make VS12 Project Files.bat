rmdir /S /Q bin
rmdir /S /Q lib
rmdir /S /Q VS12
mkdir VS12
chdir VS12
cmake -G "Visual Studio 12 2013" ..
chdir ..