@ingroup log_system

## Introduction

In some cases, taking the time to build yourself a well defined and crafted tool can save you an immense amount time in the future. In my opinion, a logging subsystem is one of those cases. It can help to root out tricky bugs by telling you when each function is being entered and exited, and the state of variables along the way. 

This tool implements the USART driver, and is a good example of the [facade pattern][Facade_Pattern_URL] in practice. Note how neither the user nor the log_system module need to know anything about how the message is sent over USART in order to send the messages. If you **would** like to know how the USART driver, see the module [here][USART_Module_URL].

## Interface



## Example Application


[Facade_Pattern_URL]: https://en.wikipedia.org/wiki/Facade_pattern

[USART_Module_URL]: https://jason-duffy.github.io/AVRly/html/group__usart.html