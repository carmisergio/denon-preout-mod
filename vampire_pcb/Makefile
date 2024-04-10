KICAD_PROJECT_DIR=kicad_project
KICAD_PCB=$(KICAD_PROJECT_DIR)/vampire_pcb.kicad_pcb
OUTPUT_DIR=output
GERBERS_DIR=$(OUTPUT_DIR)/gerbers
GERBERS_ZIP=$(OUTPUT_DIR)/vampire_pcb.zip

KICAD_CLI=kicad-cli


GERBERS_ZIP: $(KICAD_PCB)
	mkdir -p $(OUTPUT_DIR)
	mkdir -p $(GERBERS_DIR)
	rm -rf $(GERBERS_DIR)/*
	$(KICAD_CLI) pcb export drill -o $(GERBERS_DIR)/ $(KICAD_PCB)
	$(KICAD_CLI) pcb export gerbers -o $(GERBERS_DIR)/ $(KICAD_PCB)
	zip $(GERBERS_ZIP) $(GERBERS_DIR)/*

clean:
	rm -rf $(OUTPUT_DIR)
