set term png
set output "randdis.png"
plot "randconnexe.dat" w l, 0.5*(x*log(x))



