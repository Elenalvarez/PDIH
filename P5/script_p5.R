library(tuneR)
library(seewave)
library(audio)

nombre <- readMP3('nombre.mp3')
apellido <-readMP3('apellido.mp3')

plot(extractWave(nombre, from = 1, to = 393984))
plot(extractWave(apellido, from = 1, to = 393984))

mezcla <- pastew(apellido, nombre, output = "Wave")
plot(extractWave(mezcla, from = 1, to=393984))

mezclaF <- bwfilter(mezcla, channel = 1, n=1, from = 10000, 
                    to= 20000, bandpass = TRUE, listen = FALSE, output = "Wave")

writeWave(mezcla, file.path("mezcla.wav"))

mezclaEco <- echo(mezcla, f=22050, amp = c(0.8, 0.4, 0.2), delay = c(1,2,3), output = "Wave")
mezclaEco@left <- 10000 * mezclaEco@left
mezclaEcoAlreves <- revw(mezclaEco, output = "Wave")

writeWave(mezclaEcoAlreves, file.path("alreves.wav"))
