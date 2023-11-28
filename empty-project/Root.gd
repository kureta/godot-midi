extends Node2D


# Called when the node enters the scene tree for the first time.
func _ready():
	var sum = Summator.new()
	sum.add(4)
	sum.add(2)
	print(sum.get_total())
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass
