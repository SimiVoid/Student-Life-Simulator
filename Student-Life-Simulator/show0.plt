#==============================================================================
# GNUPLOT-palette (set2)
#------------------------------------------------------------------------------
# see more at https://github.com/Gnuplotting/gnuplot-palettes
#==============================================================================
# line styles for ColorBrewer Set3
# for use with qualitative/categorical data
# provides 8 hard-to-name colors
# compatible with gnuplot >=4.2
# author: Anna Schneider

# line styles
set style line 1 lt 1 lc rgb '#66C2A5' # teal
set style line 2 lt 1 lc rgb '#FC8D62' # orange
set style line 3 lt 1 lc rgb '#8DA0CB' # lilac
set style line 4 lt 1 lc rgb '#E78AC3' # magentat
set style line 5 lt 1 lc rgb '#A6D854' # lime green
set style line 6 lt 1 lc rgb '#FFD92F' # banana
set style line 7 lt 1 lc rgb '#E5C494' # tan
set style line 8 lt 1 lc rgb '#B3B3B3' # grey

# palette
set palette maxcolors 8
set palette defined ( 0 '#66C2A5',\
    	    	      1 '#FC8D62',\
		      2 '#8DA0CB',\
		      3 '#E78AC3',\
		      4 '#A6D854',\
		      5 '#FFD92F',\
		      6 '#E5C494',\
		      7 '#B3B3B3' )

#==============================================================================
# TERMINAL
#==============================================================================
set termoption enhanced
set terminal GNUTERM size 800,600
set encoding utf8
#==============================================================================
# SETUP COMMANDS
#==============================================================================
set xlabel 'Epoch' enhanced textcolor '#404040'
set ylabel 'Count' enhanced textcolor '#404040'


set border 3 front linetype 1 linewidth 2 linecolor '#404040'
unset grid
set style fill solid noborder
set style histogram
set tics border nomirror out scale 0.5,0.25 norotate enhanced textcolor '#404040' front
unset xtics
unset x2tics
set mxtics
unset mx2tics
set ytics border nomirror out scale 0.5,0.25 norotate enhanced textcolor '#404040'
unset y2tics
set mytics
unset my2tics
unset ztics
unset mztics
unset rtics
unset mrtics
set key inside right top opaque vertical Left noinvert reverse width 0 height 1 samplen 4 spacing 1 enhanced textcolor '#404040' nobox maxrows auto maxcols auto
set boxwidth 0.9 relative
set datafile missing "?"
#==============================================================================
# CUSTOM EXPLICIT GNUPLOT COMMANDS
#==============================================================================
set style data histogram
#==============================================================================
# PLOT COMMANDS
#==============================================================================
plot \
    'plot0.dat' index 0 title 'Studying Students' with lines linestyle 1 linewidth 3, \
    'plot0.dat' index 1 title 'Students failed' with lines linestyle 2 linewidth 3, \
    'plot0.dat' index 2 title 'Students passed' with lines linestyle 3 linewidth 3, \
    'plot0.dat' index 3 title 'Sleeping students' with lines linestyle 4 linewidth 3, \
    'plot0.dat' index 4 title 'Drunk students' with lines linestyle 5 linewidth 3

