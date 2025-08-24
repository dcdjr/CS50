const saved = localStorage.getItem("theme");
if (saved === "dark" || saved === "light") {
  document.documentElement.setAttribute("data-bs-theme", saved);
} else {
  // default to light if nothing saved
  document.documentElement.setAttribute("data-bs-theme", "light");
}
document.addEventListener("DOMContentLoaded", function() {
  const toggleButton = document.getElementById("dark-mode-toggle");
  const icon = document.getElementById("themeIcon");
  // make sure the icon and button match saved theme on load
  let savedTheme = localStorage.getItem("theme");
  if (savedTheme == "dark") {
    icon.classList.remove("bi-moon");
    icon.classList.add("bi-sun");
    toggleButton.classList.remove("btn-dark");
    toggleButton.classList.add("btn-light");
  } else {
    icon.classList.remove("bi-sun");
    icon.classList.add("bi-moon");
    toggleButton.classList.remove("btn-light");
    toggleButton.classList.add("btn-dark");
  }
  document
    .getElementById("dark-mode-toggle")
    .addEventListener("click", function() {
      if (document.documentElement.getAttribute("data-bs-theme") == "dark") {
        localStorage.setItem("theme", "light");
        document.documentElement.setAttribute("data-bs-theme", "light");
        localStorage.setItem("icon", "bi-moon");
        icon.classList.remove("bi-sun");
        icon.classList.add("bi-moon");
        localStorage.setItem("button_color", "btn-dark");
        toggleButton.classList.remove("btn-light");
        toggleButton.classList.add("btn-dark");
      } else {
        localStorage.setItem("theme", "dark");
        document.documentElement.setAttribute("data-bs-theme", "dark");
        localStorage.setItem("icon", "bi-sun");
        icon.classList.remove("bi-moon");
        icon.classList.add("bi-sun");
        localStorage.setItem("button_color", "btn-light");
        toggleButton.classList.remove("btn-dark");
        toggleButton.classList.add("btn-light");
      }
    });
});
