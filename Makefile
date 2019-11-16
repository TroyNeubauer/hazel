# Alternative GNU Make workspace makefile autogenerated by Premake

ifndef config
  config=debug
endif

ifndef verbose
  SILENT = @
endif

ifeq ($(config),debug)
  zlib_config = debug
  GLFW_config = debug
  Glad_config = debug
  ImGui_config = debug
  freeimage_config = debug
  FastNoiseSIMD_config = debug
  TUtil_config = debug
  Hazel_config = debug
  Sandbox_config = debug
  ImGuiTest_config = debug
  Sandbox2_config = debug
  GameDesign_config = debug

else ifeq ($(config),release)
  zlib_config = release
  GLFW_config = release
  Glad_config = release
  ImGui_config = release
  freeimage_config = release
  FastNoiseSIMD_config = release
  TUtil_config = release
  Hazel_config = release
  Sandbox_config = release
  ImGuiTest_config = release
  Sandbox2_config = release
  GameDesign_config = release

else ifeq ($(config),dist)
  zlib_config = dist
  GLFW_config = dist
  Glad_config = dist
  ImGui_config = dist
  freeimage_config = dist
  FastNoiseSIMD_config = dist
  TUtil_config = dist
  Hazel_config = dist
  Sandbox_config = dist
  ImGuiTest_config = dist
  Sandbox2_config = dist
  GameDesign_config = dist

else
  $(error "invalid configuration $(config)")
endif

PROJECTS := zlib GLFW Glad ImGui freeimage FastNoiseSIMD TUtil Hazel Sandbox ImGuiTest Sandbox2 GameDesign

.PHONY: all clean help $(PROJECTS) 

all: $(PROJECTS)

zlib:
ifneq (,$(zlib_config))
	@echo "==== Building zlib ($(zlib_config)) ===="
	@${MAKE} --no-print-directory -C Hazel/vendor/zlib -f Makefile config=$(zlib_config)
endif

GLFW:
ifneq (,$(GLFW_config))
	@echo "==== Building GLFW ($(GLFW_config)) ===="
	@${MAKE} --no-print-directory -C Hazel/vendor/GLFW -f Makefile config=$(GLFW_config)
endif

Glad:
ifneq (,$(Glad_config))
	@echo "==== Building Glad ($(Glad_config)) ===="
	@${MAKE} --no-print-directory -C Hazel/vendor/Glad -f Makefile config=$(Glad_config)
endif

ImGui:
ifneq (,$(ImGui_config))
	@echo "==== Building ImGui ($(ImGui_config)) ===="
	@${MAKE} --no-print-directory -C Hazel/vendor/imgui -f Makefile config=$(ImGui_config)
endif

freeimage:
ifneq (,$(freeimage_config))
	@echo "==== Building freeimage ($(freeimage_config)) ===="
	@${MAKE} --no-print-directory -C Hazel/vendor/freeimage -f Makefile config=$(freeimage_config)
endif

FastNoiseSIMD:
ifneq (,$(FastNoiseSIMD_config))
	@echo "==== Building FastNoiseSIMD ($(FastNoiseSIMD_config)) ===="
	@${MAKE} --no-print-directory -C Hazel/vendor/FastNoiseSIMD -f Makefile config=$(FastNoiseSIMD_config)
endif

TUtil:
ifneq (,$(TUtil_config))
	@echo "==== Building TUtil ($(TUtil_config)) ===="
	@${MAKE} --no-print-directory -C Hazel/vendor/TUtil/TUtil -f Makefile config=$(TUtil_config)
endif

Hazel: GLFW Glad ImGui freeimage FastNoiseSIMD zlib TUtil
ifneq (,$(Hazel_config))
	@echo "==== Building Hazel ($(Hazel_config)) ===="
	@${MAKE} --no-print-directory -C Hazel -f Makefile config=$(Hazel_config)
endif

Sandbox: Hazel Glad ImGui GLFW FastNoiseSIMD TUtil freeimage zlib
ifneq (,$(Sandbox_config))
	@echo "==== Building Sandbox ($(Sandbox_config)) ===="
	@${MAKE} --no-print-directory -C Sandbox -f Makefile config=$(Sandbox_config)
endif

ImGuiTest:
ifneq (,$(ImGuiTest_config))
	@echo "==== Building ImGuiTest ($(ImGuiTest_config)) ===="
	@${MAKE} --no-print-directory -C ImGuiTest -f Makefile config=$(ImGuiTest_config)
endif

Sandbox2: Hazel
ifneq (,$(Sandbox2_config))
	@echo "==== Building Sandbox2 ($(Sandbox2_config)) ===="
	@${MAKE} --no-print-directory -C Sandbox2 -f Makefile config=$(Sandbox2_config)
endif

GameDesign: Hazel
ifneq (,$(GameDesign_config))
	@echo "==== Building GameDesign ($(GameDesign_config)) ===="
	@${MAKE} --no-print-directory -C GameDesign -f Makefile config=$(GameDesign_config)
endif

clean:
	@${MAKE} --no-print-directory -C Hazel/vendor/zlib -f Makefile clean
	@${MAKE} --no-print-directory -C Hazel/vendor/GLFW -f Makefile clean
	@${MAKE} --no-print-directory -C Hazel/vendor/Glad -f Makefile clean
	@${MAKE} --no-print-directory -C Hazel/vendor/imgui -f Makefile clean
	@${MAKE} --no-print-directory -C Hazel/vendor/freeimage -f Makefile clean
	@${MAKE} --no-print-directory -C Hazel/vendor/FastNoiseSIMD -f Makefile clean
	@${MAKE} --no-print-directory -C Hazel/vendor/TUtil/TUtil -f Makefile clean
	@${MAKE} --no-print-directory -C Hazel -f Makefile clean
	@${MAKE} --no-print-directory -C Sandbox -f Makefile clean
	@${MAKE} --no-print-directory -C ImGuiTest -f Makefile clean
	@${MAKE} --no-print-directory -C Sandbox2 -f Makefile clean
	@${MAKE} --no-print-directory -C GameDesign -f Makefile clean

help:
	@echo "Usage: make [config=name] [target]"
	@echo ""
	@echo "CONFIGURATIONS:"
	@echo "  debug"
	@echo "  release"
	@echo "  dist"
	@echo ""
	@echo "TARGETS:"
	@echo "   all (default)"
	@echo "   clean"
	@echo "   zlib"
	@echo "   GLFW"
	@echo "   Glad"
	@echo "   ImGui"
	@echo "   freeimage"
	@echo "   FastNoiseSIMD"
	@echo "   TUtil"
	@echo "   Hazel"
	@echo "   Sandbox"
	@echo "   ImGuiTest"
	@echo "   Sandbox2"
	@echo "   GameDesign"
	@echo ""
	@echo "For more information, see https://github.com/premake/premake-core/wiki"