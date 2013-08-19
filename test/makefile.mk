local_dir := test

# list all test source files
tests := 

local_sources := harness.c test.c $(addprefix test_,$(tests))
local_products := test

relative_sources := $(addprefix $(local_dir)/,$(local_sources))
relative_objects := $(patsubst %.c,%.o,$(relative_sources))
relative_products := $(addprefix $(local_dir)/,$(local_products))

sources += $(relative_sources)
dependencies += $(patsubst %.c,%.d,$(relative_sources))
objects += $(relative_objects)
products += $(relative_products)

$(relative_products): $(relative_objects)

