--The game object list is specific to each level.
--If mass is set to 0 the object is not affected by gravity.

gameObjectList = {
	player = {
	--Ths object will be used as the level transition trigger.
		model = 'sphere',
		texture = 'snowSeamless.jpg',
		--position
		pos_x = 0,
		pos_y = 1,
		pos_z = 0,
		--scale
		scl_x = 1,
		scl_y = 1,
		scl_z = 1,
		--rotation
		rot_x = 0,
		rot_y = 0,
		rot_z = 0,
		--physics properties
		coll_shape = 'cylinder',
		mass = 5,
	},
	
	--Left path
	object1 = {
		model = 'box',
		texture = 'stoneSeamless.jpg',
		--position
		pos_x = 0,
		pos_y = -5,
		pos_z = 0,
		--scale
		scl_x = 4,
		scl_y = 4,
		scl_z = 4,
		--rotation
		rot_x = 0,
		rot_y = 0,
		rot_z = 0,
		--physics properties
		coll_shape = 'box',
		mass = 0,
	},
	object2 = {
		model = 'box',
		texture = 'stoneSeamless.jpg',
		--position
		pos_x = -20,
		pos_y = -15,
		pos_z = 15,
		--scale
		scl_x = 4,
		scl_y = 4,
		scl_z = 2,
		--rotation
		rot_x = 90,
		rot_y = 0,
		rot_z = 0,
		--physics properties
		coll_shape = 'box',
		mass = 0,
	},
	object3 = {
		model = 'box',
		texture = 'stoneSeamless.jpg',
		--position
		pos_x = -35,
		pos_y = -20,
		pos_z = 35,
		--scale
		scl_x = 4,
		scl_y = 2,
		scl_z = 4,
		--rotation
		rot_x = 180,
		rot_y = 0,
		rot_z = 0,
		--physics properties
		coll_shape = 'box',
		mass = 0,
	},
	object4 = {
		model = 'box',
		texture = 'stoneSeamless.jpg',
		--position
		pos_x = -25,
		pos_y = -17,
		pos_z = 50,
		--scale
		scl_x = 4,
		scl_y = 4,
		scl_z = 2,
		--rotation
		rot_x = 270,
		rot_y = 0,
		rot_z = 0,
		--physics properties
		coll_shape = 'box',
		mass = 0,
	},
		
	--Right path
	object5 = {
		model = 'box',
		texture = 'stoneSeamless.jpg',
		--position
		pos_x = 20,
		pos_y = -15,
		pos_z = 15,
		--scale
		scl_x = 4,
		scl_y = 4,
		scl_z = 2,
		--rotation
		rot_x = 90,
		rot_y = 0,
		rot_z = 0,
		--physics properties
		coll_shape = 'box',
		mass = 0,
	},
	object6 = {
		model = 'box',
		texture = 'stoneSeamless.jpg',
		--position
		pos_x = 35,
		pos_y = -20,
		pos_z = 35,
		--scale
		scl_x = 4,
		scl_y = 2,
		scl_z = 4,
		--rotation
		rot_x = 180,
		rot_y = 0,
		rot_z = 0,
		--physics properties
		coll_shape = 'box',
		mass = 0,
	},
	object7 = {
		model = 'box',
		texture = 'stoneSeamless.jpg',
		--position
		pos_x = 25,
		pos_y = -17,
		pos_z = 50,
		--scale
		scl_x = 4,
		scl_y = 4,
		scl_z = 2,
		--rotation
		rot_x = 270,
		rot_y = 0,
		rot_z = 0,
		--physics properties
		coll_shape = 'box',
		mass = 0,
	},
	
	--Middle portion of the map
	
	object8 = {
		model = 'box',
		texture = 'stoneSeamless.jpg',
		--position
		pos_x = 0,
		pos_y = -15,
		pos_z = 65,
		--scale
		scl_x = 4,
		scl_y = 4,
		scl_z = 4,
		--rotation
		rot_x = 90,
		rot_y = 90,
		rot_z = 0,
		--physics properties
		coll_shape = 'box',
		mass = 0,
	},
	
	object9 = {
		model = 'box',
		texture = 'stoneSeamless.jpg',
		--position
		pos_x = 0,
		pos_y = -15,
		pos_z = 100,
		--scale
		scl_x = 2,
		scl_y = 2,
		scl_z = 2,
		--rotation
		rot_x = 90,
		rot_y = 90,
		rot_z = 0,
		--physics properties
		coll_shape = 'box',
		mass = 0,
	},
	
	object10 = {
		model = 'box',
		texture = 'stoneSeamless.jpg',
		--position
		pos_x = 0,
		pos_y = -15,
		pos_z = 125,
		--scale
		scl_x = 2,
		scl_y = 2,
		scl_z = 2,
		--rotation
		rot_x = 90,
		rot_y = 180,
		rot_z = 0,
		--physics properties
		coll_shape = 'box',
		mass = 0,
	},	
	
	--Final portion of the level
	leveltrigger = {
	--Ths object will be used as the level transition trigger.
		model = 'box',
		texture = 'sandSeamless.jpg',
		--position
		pos_x = 0,
		pos_y = -20,
		pos_z = 150,
		--scale
		scl_x = 8,
		scl_y = 4,
		scl_z = 8,
		--rotation
		rot_x = 0,
		rot_y = 0,
		rot_z = 0,
		--physics properties
		coll_shape = 'box',
		mass = 0,
	},
}