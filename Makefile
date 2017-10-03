all: julia image

julia:
	$(CC) -o julia julia.c

julia-xeonphi:
	icc -axMIC-AVX512,CORE-AVX2 -offload-attribute-target=mic -qopenmp -o julia julia.c

image:
	./julia; python visualize.py

largeimage:
	./julia 2000; python visualize.py

clean:
	rm -f julia julia.txt
