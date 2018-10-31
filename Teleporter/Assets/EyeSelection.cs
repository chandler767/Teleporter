using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.XR.MagicLeap;
// Tracks the fixation point of the users eyes and selects a game object when user gazes at it.
// When the controller trigger is pulled a message is published to a channel that is used to determine the ownership of the game object.

public class ControlSelection : MonoBehaviour {
    public GameObject Camera;
    public Material FocusedMaterial, NonFocusedMaterial; // User looking and user not looking.

    private MeshRenderer meshRenderer; // The game object.
    private Vector3 _heading; // Where the user looking.
    private bool looking;

    void Start () {
        MLEyes.Start(); // Start eye tracking.
        MLInput.Start(); // Start input controller.
        MLInput.OnTriggerDown += HandleOnTriggerDown; // Get trigger down event.

        meshRenderer = gameObject.GetComponent<MeshRenderer>(); // Get the game object.
    }
    
    void OnDestroy () { // Stop eye tracking and inputs.
        MLEyes.Stop();
        MLInput.OnTriggerDown -= HandleOnTriggerDown;
        MLInput.Stop();
    }

    void Update () {
        if (MLEyes.IsStarted) {
            RaycastHit rayHit = new RaycastHit();
            _heading = MLEyes.FixationPoint - Camera.transform.position;
            if (Physics.Raycast(Camera.transform.position, _heading, out rayHit, 10.0f)) { // Check for collisions of user's eye gaze with a game object.
                if (rayHit.collider.name == meshRenderer.name) { // Check if collision is with this game object.
                    meshRenderer.material = FocusedMaterial;  
                    looking = true;
                }
            }
            else { // User is not looking.
                meshRenderer.material = NonFocusedMaterial; 
                looking = false;
            }   
        }
    }

    void HandleOnTriggerDown(byte controllerId, float value) {
        if (looking) { // Send a message to take the game object if the user is looking and the trigger was pulled.
            Destroy(meshRenderer,.5f);
            GameObject.Find("CountText").GetComponent<Countdown>().power = GameObject.Find("CountText").GetComponent<Countdown>().power+1; // Update countdown.
        }
    }
}