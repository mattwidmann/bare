# directory where makefile.mk is located
local_dir := 

# source files relative to local directory
local_sources := 

sources += $(addprefix $(local_dir)/,$(local_sources))
objects += $(addprefix $(local_dir)/,$(patsubst %.c,%.o,$(local_sources)))
dependencies += $(addprefix $(local_dir)/,$(patsubst %.c,%.d,$(local_sources)))

