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

	object1 = {
		model = 'box',
		texture = 'sandSeamless.jpg',
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
		texture = 'sandSeamless.jpg',
		--position
		pos_x = 15,
		pos_y = -5,
		pos_z = 30,
		--scale
		scl_x = 2,
		scl_y = 2,
		scl_z = 2,
		--rotation
		rot_x = 0,
		rot_y = 0,
		rot_z = 0,
		--physics properties
		coll_shape = 'box',
		mass = 0,
	},
	
	object3 = {
		model = 'box',
		texture = 'sandSeamless.jpg',
		--position
		pos_x = -15,
		pos_y = -5,
		pos_z = 60,
		--scale
		scl_x = 2,
		scl_y = 2,
		scl_z = 2,
		--rotation
		rot_x = 0,
		rot_y = 0,
		rot_z = 0,
		--physics properties
		coll_shape = 'box',
		mass = 0,
	},
	
	object4 = {
		model = 'box',
		texture = 'sandSeamless.jpg',
		--position
		pos_x = 0,
		pos_y = -2,
		pos_z = 80,
		--scale
		scl_x = 2,
		scl_y = 2,
		scl_z = 2,
		--rotation
		rot_x = 0,
		rot_y = 0,
		rot_z = 0,
		--physics properties
		coll_shape = 'box',
		mass = 0,
	},
	
	object5 = {
		model = 'box',
		texture = 'sandSeamless.jpg',
		--position
		pos_x = 15,
		pos_y = 0,
		pos_z = 90,
		--scale
		scl_x = 2,
		scl_y = 2,
		scl_z = 2,
		--rotation
		rot_x = 0,
		rot_y = 0,
		rot_z = 0,
		--physics properties
		coll_shape = 'box',
		mass = 0,
	},
	
	object6 = {
		model = 'box',
		texture = 'sandSeamless.jpg',
		--position
		pos_x = 40,
		pos_y = 0,
		pos_z = 90,
		--scale
		scl_x = 6,
		scl_y = 2,
		scl_z = 2,
		--rotation
		rot_x = 0,
		rot_y = 0,
		rot_z = 0,
		--physics properties
		coll_shape = 'box',
		mass = 0,
	},
	
	object7 = {
		model = 'box',
		texture = 'sandSeamless.jpg',
		--position
		pos_x = 70,
		pos_y = -10,
		pos_z = 120,
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
	
	object8 = {
		model = 'box',
		texture = 'sandSeamless.jpg',
		--position
		pos_x = 100,
		pos_y = -20,
		pos_z = 150,
		--scale
		scl_x = 6,
		scl_y = 6,
		scl_z = 6,
		--rotation
		rot_x = 0,
		rot_y = 0,
		rot_z = 0,
		--physics properties
		coll_shape = 'box',
		mass = 0,
	},
	
	object9 = {
		model = 'box',
		texture = 'sandSeamless.jpg',
		--position
		pos_x = 120,
		pos_y = -30,
		pos_z = 170,
		--scale
		scl_x = 1,
		scl_y = 1,
		scl_z = 1,
		--rotation
		rot_x = 0,
		rot_y = 0,
		rot_z = 0,
		--physics properties
		coll_shape = 'box',
		mass = 0,
	},
	
	endTrigger = {
		model = 'castle',
		texture = 'sandSeamless.jpg',
		--position
		pos_x = 200,
		pos_y = -30,
		pos_z = 250,
		--scale
		scl_x = 20,
		scl_y = 20,
		scl_z = 20,
		--rotation
		rot_x = 0,
		rot_y = 0,
		rot_z = 0,
		--physics properties
		coll_shape = 'box',
		mass = 0,
	},
	
	castleFloor = {
		model = 'box',
		texture = 'sandSeamless.jpg',
		--position
		pos_x = 200,
		pos_y = -70,
		pos_z = 250,
		--scale
		scl_x = 40,
		scl_y = 15,
		scl_z = 40,
		--rotation
		rot_x = 0,
		rot_y = 0,
		rot_z = 0,
		--physics properties
		coll_shape = 'box',
		mass = 0,
	},
}