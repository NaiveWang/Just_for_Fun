#!/bin/bash
python extract.py
L=$( wc -l o.txt|cut -d " " -f1 )

T=$(( $L * 9 / 10 ))

echo $T $L
split -l $T o.txt
mv xaa ../NeuralNLP-NeuralClassifier/data/gen.json.00.00
mv xab ../NeuralNLP-NeuralClassifier/data/gen.json.00.01
rm o.txt
