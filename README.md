### gmodule

```
1. Apply apply.diff to gecko
2. Copy gecko.dom.webild.Gmodule.webidl to gecko/dom/webidl/
3. rm out and obj-gecko directory, then build.
```


####flow chat:  
```
  navigator.mozGmodule
          |
      Gmodule (webidl)

      /            \ 
              GmoduleChild

                     | ( ipdl) 
                 GmoduleParent

                      |

                GmoduleManager  (xpcom)

                       |
                    GmoduleService
```