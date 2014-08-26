all: html

html: index.html

index.html: index.html.in ../readme.md
	$(SED) -e '/@@readme_contents@@/{r ../readme.md' -e 'd}' $< > $@

clean:
	$(RM) index.html

.PHONY: all clean html
