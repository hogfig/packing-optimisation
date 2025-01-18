default:
	/Users/robertjelic/Documents/C++/Ellipses/build/app/EA_APP
	python ./python_scripts/visualizeFitnessScore.py ./app/CSV_Files/fitness_scores.txt&
	python ./python_scripts/animatePopulations.py ./app/CSV_Files/best_score.txt&

visualize_best_population:
	python ./python_scripts/visualizePopulation.py ./app/CSV_Files/best_score.txt

