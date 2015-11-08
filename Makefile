all:
	python setup.py build_ext -if

clean:
	-rm -r CALC.cpp build
