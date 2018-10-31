using System.Collections;
using System.Collections.Generic;
using UnityEngine.SceneManagement;
using UnityEngine;

public class EndGame : MonoBehaviour {
	void Start () {
		StartCoroutine(NextScene());
	}

	IEnumerator NextScene()
    {
        yield return new WaitForSeconds(15.0f);
        SceneManager.LoadScene(0); // Start over.
    }
}
