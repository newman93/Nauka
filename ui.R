# Prosta aplikacja webowa
# Zbiór danych: Wydatki na sprzęt elektorniczny ze względu na płeć oraz status zawodowy

library(shiny)

shinyUI(pageWithSidebar(
  
  titlePanel("Wydatki na sprzęt elektorniczny"),
  
    sidebarPanel(
      tags$head(
        tags$style("@import url(http://fonts.googleapis.com/css?family=Arbutus+Slab);; body {color: grey; font-family: 'Arbutus Srab', serif;}")
      ),
      selectInput("variable", "Wydatki ze względu na:",
                  c("Status zawodowy" = "status",
                    "Płeć" = "płeć")),
    
      checkboxInput("outliers", "Pokaż obserwacje odstające", FALSE),
      downloadLink("downloadData", "Pobierz Dane")
    ),
    
    mainPanel(    
      tabsetPanel(  
      tabPanel(title = "Wydatki", plotOutput("wydatkiPlot")),
      tabPanel(title = "Płeć", plotOutput("płećPlot")),
      tabPanel(title = "Status", plotOutput("statusPlot"))
      )
   )
))
