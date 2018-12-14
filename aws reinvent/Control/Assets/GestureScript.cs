using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.XR.MagicLeap;
using PubNubAPI;


public class GestureScript : MonoBehaviour {

    public Text onText;
    public Image onGesture;
    public float onTimeLeft;
    public Text offText;
    public Image offGesture;
    public float offTimeLeft;

    public float sendTimeController;

    public static PubNub pubnub;

    private MLHandKeyPose[] gestures; // Holds the different hand poses we will look for.

    void Awake ()
    {
        
        PNConfiguration pnConfiguration = new PNConfiguration();
        pnConfiguration.PublishKey = "pub-c-ae388464-6b8a-430e-be0a-64377c198dda";
        pnConfiguration.SubscribeKey = "sub-c-77c1dde4-dc65-11e8-b7c4-3e16c06ff365";
        pnConfiguration.Secure = true;
        pubnub = new PubNub(pnConfiguration);

        onText = GameObject.Find("OnText").GetComponent<Text>();
        onGesture = GameObject.Find("onGesture").GetComponent<Image>();
        offText = GameObject.Find("OffText").GetComponent<Text>();
        offGesture = GameObject.Find("offGesture").GetComponent<Image>();

        MLHands.Start(); // Start the hand tracking.
        gestures = new MLHandKeyPose[2]; //Assign the gestures we will look for.
        gestures[0] = MLHandKeyPose.Fist;
        gestures[1] = MLHandKeyPose.Thumb;
        MLHands.KeyPoseManager.EnableKeyPoses(gestures, true, false); // Enable the hand poses.
    }
    
    void OnDestroy()
    {
        MLHands.Stop();
    }

    void Update()
    {

        if (sendTimeController <= Time.deltaTime) { // Restrict how often messages can be sent.
            if (GetGesture(MLHands.Left, MLHandKeyPose.Thumb) || GetGesture(MLHands.Right, MLHandKeyPose.Thumb)) {
                pubnub.Publish()
                    .Channel("tp")
                    .Message("on")
                    .Async((result, status) => {    
                        if (!status.Error) {
                            Debug.Log(string.Format("Publish Timetoken: {0}", result.Timetoken));
                        } else {
                            Debug.Log(status.Error);
                            Debug.Log(status.ErrorData.Info);
                        }
                    });
                onText.color = Color.green; // Set color to green.
                onGesture.color = Color.green; // Set color to green.
                onTimeLeft = 1.0f; // Transition color back to white.
                sendTimeController = 0.5f; // Stop multiple messages from being sent.
            } else if (GetGesture(MLHands.Left, MLHandKeyPose.Fist) || GetGesture(MLHands.Right, MLHandKeyPose.Fist)) {
                pubnub.Publish()
                    .Channel("tp")
                    .Message("off")
                    .Async((result, status) => {    
                        if (!status.Error) {
                            Debug.Log(string.Format("Publish Timetoken: {0}", result.Timetoken));
                        } else {
                            Debug.Log(status.Error);
                            Debug.Log(status.ErrorData.Info);
                        }
                    });
                offText.color = Color.green; // Set color to green.
                offGesture.color = Color.green; // Set color to green.
                offTimeLeft = 1.0f; // Transition color back to white.
                sendTimeController = 0.5f; // Stop multiple messages from being sent
            }
        } else {
            sendTimeController -= Time.deltaTime; // Update the timer.
        }

        if (onTimeLeft > Time.deltaTime) {
            onText.color = Color.Lerp(onText.color, Color.white, Time.deltaTime / onTimeLeft); // Calculate interpolated color.
            onGesture.color = Color.Lerp(onGesture.color, Color.white, Time.deltaTime / onTimeLeft); // Calculate interpolated color.
            onTimeLeft -= Time.deltaTime; // Update the timer.
        }
        if (offTimeLeft > Time.deltaTime) {
            offText.color = Color.Lerp(offText.color, Color.white, Time.deltaTime / offTimeLeft); // Calculate interpolated color.
            offGesture.color = Color.Lerp(offGesture.color, Color.white, Time.deltaTime / offTimeLeft); // Calculate interpolated color.
            offTimeLeft -= Time.deltaTime; // Update the timer.
        }
    }

    bool GetGesture(MLHand hand, MLHandKeyPose type)
    {
        if (hand != null)
        {
            if (hand.KeyPose == type)
            {
                if (hand.KeyPoseConfidence > 0.99f)
                {
                    return true;
                }
            }
        }
        return false;
    }
}
