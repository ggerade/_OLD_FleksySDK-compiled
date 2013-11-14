FQP_ARGS ?= -ip -e -a -q s10 n20 w200

ASSETS_LANGUAGES = bg-BG cs-CZ da-DK de-DE el-GR en-US es-ES et-EE fi-FI fr-FR hr-HR hu-HU it-IT lt-LT ms-MY nb-NO nl-NL pl-PL pt-BR pt-PT ro-RO ru-RU sk-SK sv-SE uk-UA
# tr-TR

.PHONY: all $(ASSETS_LANGUAGES)

all: $(ASSETS_LANGUAGES)

$(ASSETS_LANGUAGES): FleksyTester.jar
	@/usr/bin/perl -C -e '$$FQP=`java -Xmx2048M -jar FleksyTester.jar $(FQP_ARGS) -loc:$@ 2>&1`; print("vvvvv $@ vvvvv\n" . $$FQP . "^^^^^ $@ ^^^^^^\n\n");'

JAVA_SRCS = src/engine/Converter.java src/engine/Definer.java src/engine/FleksyEngine.java src/engine/NoiseMaker.java src/engine/Reader.java src/engine/TestEngine.java src/utils/Client.java src/utils/DataManager.java src/utils/Debugger.java src/utils/FleksyInterface.java src/utils/Key.java src/utils/Log.java src/utils/Point.java src/utils/Touch.java src/utils/Word.java src/views/FleksTest.java

FleksyTester.jar: $(JAVA_SRCS) Scripts/buildFleksyTester.sh
	@echo "Building FleksyTester..."
	@Scripts/buildFleksyTester.sh
