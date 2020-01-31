# -----------------------------------
#	 	Linux shell script file
# -----------------------------------

echo $0 $1 $2 $3
echo "PWD : $1"
echo "OUT_PWD : $2"
echo "TARGET : $3"

#cp -fr $1/*.h 		$1/../include

# Copy Library
#cp -v $1/../ItLib/$3/lib/*.so*		$1/$3/lib/
cp -v $1/../ItLibSMRT/$3/lib/*.so*		$1/$3/lib/

#cp -v $2/*.so*				$1/../$3/lib/
