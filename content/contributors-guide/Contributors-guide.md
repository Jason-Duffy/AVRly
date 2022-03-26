# Contributor's Guide

Contibutions to AVRly are more than welcome!

If you feel you could improve on a module in this collection, or add new modules for other components users might like to see, it would be great to have you involved! Contributors will be credited on the site and in Copyright notices in each file they worked on.


## Style Guide

For a comprehensive guide on layout, style and documentation, see the [Anatomy of Embedded Firmware][Firmware_Anatomy_URL] page. For even more detail on this, see the [Barr Group C Coding Standard][Barr_Coding_Standard_URL]. Modularity and compartmentalisation are key for ease of maintainance and code re-use, just because this isn't C++ doesn't mean we have to throw away all those object oriented principles! If you want to extend a module in this collection to provide an extra layer of functionality for a specific purpose, the [facade pattern][Facade_Wiki_URL] should be used. For an example on this, see the [log system module][Log_System_URL] and observe how the USART driver is implemented, hiding it's inner workings from the layer above. 

## Templates

The [Github repository][Github_Repo_URL] contains [templates for each file type][Templates_URL] mentioned in the [Anatomy of Embedded Firmware][Firmware_Anatomy_URL] guide. These templates will provide the bare-bones file structure for your project, along with a Makefile to assist with building and compiling your application. 

## What to Avoid

Try to keep drivers and modules concise. Each driver should perform a specific set of tasks well, and should expose the least possible data from within the source code. To share data between files, queues and/or getter and setter functions should be used to return data, rather than using `extern` variables in the header file (where possible).

Avoid using bulky standard library functions as these can link in alot of unwanted code. Instead, it's sometimes better to provide your own stripped back implementation of these functions. That doesn't mean don't use the standard library of course, just have some awareness of the overhead of external code. 

## Submitting a Pull Request


[Firmware_Anatomy_URL]: https://jason-duffy.github.io/AVRly/html/md_content_anatomy_of_embedded_firmware__anatomy.html

[Barr_Coding_Standard_URL]: https://barrgroup.com/sites/default/files/barr_c_coding_standard_2018.pdf

[Facade_Wiki_URL]: https://en.wikipedia.org/wiki/Facade_pattern

[Github_Repo_URL]: https://github.com/Jason-Duffy/AVRly

[Templates_URL]: https://github.com/Jason-Duffy/AVRly/tree/main/content/modules/templates