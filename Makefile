build: star_dust

star_dust: star_dust.c
	gcc star_dust.c -o star_dust -Wall

clean:
	rm -f star_dust

