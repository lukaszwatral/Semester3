#! /bin/bash
#SO IS1 224A LAB07
#Łukasz Watral
#lukasz_watral@zut.edu.pl

choice=$1

case $choice in
    -l)

for mod in /sys/module/*
do
    if [ -e $mod/refcnt ]
    then
       mod_name=${mod:12}
       mod_nr=$(cat $mod/refcnt)
       holders=()
       echo -en $mod_name "\t" $mod_nr" "
       holders+=(`ls $mod/holders`)
       echo -n ${holders[0]}
       vec_len=${#holders[*]}
       for((i=1; i<vec_len; i++))
       do
      	 echo -n ",${holders[i]}"
       done
       echo
    fi
done
;;

-b)

for mod in /sys/module/*
do
    if [ ! -e $mod/refcnt ]
    then
    	mod_name=${mod:12}
    	parameters=()
    	echo -en "$mod_name\t"
    	if [ -d $mod/parameters ]
    	then
    		parameters+=(`ls $mod/parameters`)
    		echo -n ${parameters[0]}
    		vec_len=${#parameters[*]}
    		for((i=1; i<vec_len; i++))
       		do
       			echo -n ",${parameters[i]}"
       		done
       echo
       else
       echo
       fi
     fi
done
;;

*)
	echo "Użyj [ -b | -l ]"
;;
esac
