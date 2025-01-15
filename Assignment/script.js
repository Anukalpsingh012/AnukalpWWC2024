let audioPlayer = null;

function uploadScript() {
    const fileInput = document.getElementById('script-upload');
    const feedback = document.getElementById('upload-feedback');
    const display = document.getElementById('script-display');
    const copyButton = document.getElementById('copy-text');

    if (fileInput.files.length === 0) {
        feedback.innerText = "Please select a file to upload.";
        return;
    }

    const file = fileInput.files[0];
    const reader = new FileReader();
    reader.onload = function () {
        feedback.innerText = "Script uploaded successfully!";
        display.innerText = reader.result;
        copyButton.disabled = false; // Enable the Copy Text button
    };
    reader.readAsText(file);
}

function copyText() {
    const display = document.getElementById('script-display');
    const text = display.innerText;

    if (!text) {
        alert("No text to copy!");
        return;
    }

    // Use Clipboard API to copy the text
    navigator.clipboard.writeText(text).then(() => {
        alert("Text copied to clipboard!");
    }).catch(err => {
        console.error("Failed to copy text: ", err);
    });
}

function playAudio(file) {
    if (audioPlayer) audioPlayer.pause();
    audioPlayer = new Audio(file);
    audioPlayer.play();
}

function pauseAudio() {
    if (audioPlayer) audioPlayer.pause();
}

function resetAudio() {
    if (audioPlayer) {
        audioPlayer.pause();
        audioPlayer.currentTime = 0;
    }
}

function playTextDescription() {
    const text = document.getElementById('scene-text').value.trim();
    const rate = parseFloat(document.getElementById('speech-rate').value);
    const pitch = parseFloat(document.getElementById('speech-pitch').value);
    if (!text) {
        alert("Please enter some text to describe the scene.");
        return;
    }

    const speech = new SpeechSynthesisUtterance(text);
    speech.lang = 'en-US';
    speech.pitch = pitch;
    speech.rate = rate;
    window.speechSynthesis.speak(speech);
}

function navigateScene(sceneName) {
    document.getElementById('current-scene').innerText = `You are now at: ${sceneName}`;
}

// Eco-Friendly Tracking and Rewards
function addEcoAction() {
    const name = document.getElementById('userName').value;
    const action = document.getElementById('ecoAction').value;
    
    let userData = JSON.parse(localStorage.getItem(name)) || { name, ecoPoints: 0, ecoActions: [] };
    userData.ecoActions.push(action);
    userData.ecoPoints += 10;
    localStorage.setItem(name, JSON.stringify(userData));

    alert('Eco-friendly action added!');
}

function getUserData() {
    const name = document.getElementById('getUserName').value;
    const userData = JSON.parse(localStorage.getItem(name));

    if (userData) {
        document.getElementById('userData').innerHTML = `
            <p>Name: ${userData.name}</p>
            <p>Eco Points: ${userData.ecoPoints}</p>
            <p>Eco Actions: ${userData.ecoActions.join(', ')}</p>
        `;
    } else {
        document.getElementById('userData').innerHTML = `<p>User not found.</p>`;
    }
}

// Example audio files (replace with your actual file paths)
const audioFiles = {
    'Scene 1: Introduction': 'audio1.mp3',
    'Scene 2: Conflict': 'audio2.mp3',
    'Scene 3: Resolution': 'audio3.mp3'
};

function playPreloadedAudio(scene) {
    const audioFile = audioFiles[scene];
    if (audioFile) {
        playAudio(audioFile);
    } else {
        alert("Audio file not found for " + scene);
    }
}
