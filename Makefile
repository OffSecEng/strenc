LIBRARIES = -Iinclude
SOURCES = ./cmd/strenc.c
OUTPUT_DIR = ./bin
OUTPUT = -o ${OUTPUT_DIR}/PROG
INSTALL_OUTPUT = ${OUTPUT_DIR}/PROG

build: output_dir
	gcc -Wall ${SOURCES} ${OUTPUT:PROG=strenc} ${LIBRARIES} 

debug: output_dir
	gcc -Wall -g ${SOURCES} ${OUTPUT:PROG=strenc} ${LIBRARIES}

output_dir:
	mkdir -p ${OUTPUT_DIR}

clean:
	rm -rf $(OUTPUT_DIR) ${CERT_DIR} **.h.gch

