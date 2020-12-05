all:
	python3 setup.py build_ext -if

clean:
	-rm -r CALC.cpp build
	-rm *.so
