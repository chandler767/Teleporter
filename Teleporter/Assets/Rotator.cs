using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Rotator : MonoBehaviour {
	void Start()
    {
        GetComponent<Rigidbody>().angularVelocity = Vector3.right * 2.0f;
    }
}
